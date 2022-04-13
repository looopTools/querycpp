FROM fedora:latest

RUN dnf -y upgrade
RUN dnf -y install wget emacs clang git cmake zip postgresql-server postgresql-contrib
RUN dnf -y install libpq-devel
RUN wget https://github.com/jtv/libpqxx/archive/refs/tags/7.7.2.zip
RUN unzip 7.7.2.zip
RUN /usr/bin/postgresql-setup --initdb
RUN systemctl enable --now postgresql
