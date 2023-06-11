FROM ubuntu:latest

RUN apt-get update && \
    apt-get -y install \
    check lcov clang-format valgrind cppcheck cmake pkg-config build-essential \
    mesa-utils libglfw3-dev

COPY . /code
WORKDIR /code/src/

CMD bash
