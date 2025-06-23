#!/bin/sh -e
redo-ifchange foo.txt
echo "zbudowano: $(cat foo.txt)"
