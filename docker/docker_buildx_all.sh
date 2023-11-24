#!/usr/bin/env bash
set -e

read -n 1 -p "Create new builder instance? [y/n] " REPLY
if [[ $REPLY == [yY]* ]]; then
    docker buildx create --name c-programming-cookbook-builder
    docker buildx use c-programming-cookbook-builder
    docker buildx inspect --bootstrap
fi

USER=gilbertfrancois
REPO=c-programming-cookbook
VERSION=1.1

docker buildx build --platform=linux/amd64,linux/arm64 \
    --tag ${USER}/${REPO}:${VERSION} \
    --tag ${USER}/${REPO}:latest \
    -f Dockerfile \
    --push \
    .
