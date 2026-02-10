# Ansic

> Generate terminal ANSI C escape code

- ANSI_escape_code: https://en.wikipedia.org/wiki/ANSI_escape_code

## Install (Mac)

```shell
curl -L https://github.com/mazezen/ansic/releases/download/v1.0.0/ansic \
     -o /tmp/ansic && \
sudo mv /tmp/ansic /usr/local/bin/ansic && \
sudo chmod +x /usr/local/bin/ansic
```

## Usage

Reset

```shell
$ ansic 0
$ \033[0m
```

Red

```shell
$ ansic red
$ \033[31m
```

bgmagenta

```shell
$ ansic bgmagenta
$ \033[45m
```
