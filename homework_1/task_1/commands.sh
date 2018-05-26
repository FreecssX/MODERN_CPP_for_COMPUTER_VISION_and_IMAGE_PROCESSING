#!/bin/bash
cat ./data/data.dat | wc -l
grep d[oa]lor ./data/data.dat | wc -l
cat ./data/data.dat | wc -w
grep -o '\<mol' ./data/data.dat | wc -l
ls -l ./data/test_folder/*.txt | wc -l
