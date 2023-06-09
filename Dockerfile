FROM carlonluca/qt-dev:6.5.1

RUN apt-get update && \
    apt-get -y install check lcov clang-format valgrind cppcheck

WORKDIR /code/src/

CMD bash
