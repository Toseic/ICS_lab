

#include "cachelab.h"
#include <getopt.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef long Addr;

int need_detail = 0;
int s, E, b, t;
char * T;
char addr_c[64];
char num_c[64];
long hits,misses,evictions;

typedef struct line_ {
    int valid;
    long tag;
} Line;

typedef struct set_ {
    Line lines[5];
    // the first is the newest one, pls kill lines_map[E-1]  
    int lines_map[5]; 
} Set;

Set mem[65];

// init lines_map
void init_set(Set* st) {
    for (int i=0;i<E;++i) {
        st->lines_map[i] = i;
        st->lines[i].valid = 0;
    }
}
 
// fresh LRU map, run this func after new tag(miss) already store in the lines[].
void fresh_line_map(Set* st, int new_point ) { 
    if (E == 1) return;
    int i;
    for (i=0;i<E;++i) {
        if (st->lines_map[i] == new_point) break;
    }
    for (int j=i;j>0;--j) {
        st->lines_map[j] = st->lines_map[j-1];
    }
    st->lines_map[0] = new_point;
}




void cut(Addr addr, long* tag, long* set, long* block) {
    long tag_mask = ((1<<t)-1)<<(64-t);
    long tag_mask_r = ((1L<<t)-1);
    long set_mask= ((1<<s)-1)<<(b);
    long block_mask = (1<<b) - 1;

    *tag = ((addr&tag_mask)>>(64-t))&tag_mask_r;
    *set = (addr&set_mask)>>(b);
    *block = addr&block_mask;
}

void action(char cmd, long tag, int set, int block) {
    Set *cset = &mem[set];
    int found = 0;
    int found_p = -1;
    // only read, no write
    for (int i=0;i<E;++i) {
        if ((cset->lines[i].valid) && (cset->lines[i].tag == tag)) {
            found = 1;
            found_p = i;
        }
    }
    if (need_detail) {
        printf("%c %s,%s ",cmd,addr_c,num_c);
        if (found) printf("hit");
        else printf("miss");
    }

    // global counter
    if (found) {
        ++hits;
        if (cmd == 'M') ++hits;
    } 
    else ++misses;

    // write cmd
    if (!found) {
        int find_empty = 0;
        int chosd;
        for (chosd=0;chosd<E;++chosd) {
            if (! cset->lines[chosd].valid) {
                find_empty = 1;  break;
            }
        }
        if (!find_empty) {
            chosd = cset->lines_map[E-1];
            ++ evictions;
            if (need_detail) printf(" eviction");
        }
        cset->lines[chosd].valid = 1;
        cset->lines[chosd].tag = tag;
        fresh_line_map(cset,chosd);
    } else { // found
        fresh_line_map(cset, found_p);
    }
    if (need_detail) {
        // dbg 
        printf(" %lx %lx %d %d",mem[0].lines[0].tag,mem[0].lines[1].tag,
        mem[0].lines_map[0],mem[0].lines_map[1]);
        // dbg 
        printf("\n");
    } 
}

int main(int argc, char* argv[]) {
    int opt;
    char * data;   char point_c;
    hits = 0; misses = 0; evictions = 0;
    data = (char *)malloc(sizeof(char)*200);
    // int counter = 0;
    while((opt=getopt(argc,argv,"v::s:E:b:t"))!=EOF) { // without any legal check
        switch(opt){
            case 'v': 
                need_detail = 1;  break;
            case 's':
                s = atoi(optarg); break;
            case 'E': 
                E = atoi(optarg); break;
            case 'b': 
                b = atoi(optarg); break;
            case 't': 
                T = argv[optind]; break;
        }
    }
    t = 64 - (s + b);

    // init each set,
    for (int i=0;i<s;++i) {
        init_set(&mem[i]);
    }

    int line = 0; // line = 0 or 1
    FILE *f_p = fopen(T,"r");
    char cmd = ' ';
    while(!feof(f_p)) {
        Addr addr;
        memset(addr_c, 0, sizeof(addr_c));
        memset(num_c, 0, sizeof(num_c));
    
        fscanf(f_p,"%s",data);
        if (!line) { // line 0: L, S, M
            cmd = data[0];
            if (cmd) line = 1;          
        } else { // line 1: addr,num
            int i;
            long tag;
            long set, block;
            for (i=0;i<31;++i) {
                point_c = data[i];
                if (point_c == ',') break;
                addr_c[i] = point_c;
            }
            ++i;
            for (int j=0;i<31;++i,++j) {
                point_c = data[i];
                if (!point_c) break;
                num_c[j] = data[i];
            }
            addr = strtol(addr_c, NULL, 16);
            cut(addr, &tag, &set, &block);
            action(cmd, tag, set, block);
            line = 0;
        }
    }
    
    fclose(f_p);
    free(data);
    data = NULL;
    printSummary(hits,misses,evictions);
    return 0;
}