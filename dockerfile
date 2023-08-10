FROM python:slim

RUN apt -y update && apt -y install git

RUN apt -y install gcc cppcheck clang clang-format make gdb

WORKDIR /mnt
