FROM gcc:latest

RUN apt-get update \
    && apt-get install -y \
        cmake \
        gcovr \
        cppcheck \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
