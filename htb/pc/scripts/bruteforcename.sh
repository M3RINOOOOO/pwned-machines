#!/bin/bash

while read -r name;
do
  echo $name
  echo grpc_cli 10.10.11.214:50051 RegisterUser "username: '$name', password: 'tetas'"
done < $1


