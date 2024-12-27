FROM gcc:14.2.0

RUN apt-get update && apt-get install -y \
    cmake \
    strace \
    libzmq3-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
