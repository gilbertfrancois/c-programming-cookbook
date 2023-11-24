set -e

# Create a new builder instance, if not already created
docker buildx create --name c-programming-cookbook-builder
docker buildx use c-programming-cookbook-builder
docker buildx inspect --bootstrap

USER=gilbertfrancois
REPO=c-programming-cookbook
VERSION=1.0

docker buildx build --platform=linux/amd64,linux/arm64 \
    --tag ${USER}/${REPO}:${VERSION} \
    --tag ${USER}/${REPO}:latest \
    -f Dockerfile \
    --push \
    .
