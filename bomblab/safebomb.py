#!/usr/bin/env python3

# Author: Tosey
# datetime: 2022-09-25

import os

with open("./bomb","rb") as f1:
    bomb_r = f1.read()
    
    init_func_start = b"\xf3\x0f\x1e\xfa\x55\x53\x48\x81"
    init_func_replace = b"\xc3\x00\x00\x00\x00\x00\x00\x00"
    token_compare = b"\x81\x38\x11\xfa\x22\x20"
    token_compare_replace = b"\x39\xd8\x39\xd8\x39\xd8"
    if init_func_start not in bomb_r or token_compare not in bomb_r:
        print("maybe something is wrong in your file  :(")
        exit()
    bomb_w = bomb_r.replace(init_func_start,init_func_replace)
    bomb_w = bomb_w.replace(token_compare,token_compare_replace)
    with open("./safebomb","wb") as f2:
        f2.write(bomb_w)
        print(
        """ 	    success! :)
            you can find safebomb in ./safebomb, ENJOY your bomblab!!!
            """)
        try:
            os.system("chmod 775 ./safebomb")
        except Exception as e:
            print(
        """
            please run command: 'sudo chmod 775 ./safebomb'
            so that you can run this file.
            """
            )

            
            
            
            