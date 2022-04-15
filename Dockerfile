RUN apt-get upgrade
RUN apt-get -y install build-essential wget zip 
RUN bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
RUN wget https://github.com/jtv/libpqxx/archive/refs/tags/7.7.2.zip
RUN unzip 7.7.2.zip