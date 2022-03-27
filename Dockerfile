FROM alpine:latest as base
WORKDIR /src
RUN apk update && apk upgrade \
&& apk add --no-cache g++ \
&& apk add --no-cache cmake

COPY . /src
RUN g++ -Wall -Wextra -Werror src/mainframe.cpp PogVM 

CMD ["./PogVM"]