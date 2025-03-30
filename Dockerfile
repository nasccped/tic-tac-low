FROM alpine:3.21.3
WORKDIR /tic-tac-low
RUN apk update && apk upgrade
RUN apk add gcc make musl-dev binutils
COPY . .
RUN make build
CMD ["make", "run", "clean"]
