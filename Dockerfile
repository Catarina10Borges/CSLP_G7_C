FROM gcc:4.9

MAINTAINER catarinaborges

COPY . /home/catarina/Desktop/CSLP/projeto1/cslp_c/balanca

WORKDIR /home/catarina/Desktop/CSLP/projeto1/cslp_c/balanca

CMD ["./balanca/main.c"]
