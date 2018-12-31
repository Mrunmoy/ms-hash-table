# Use an official gcc image as base
FROM gcc:7.3

# Install dependencies
RUN apt-get update
RUN apt-get install -y python python-pip wget
RUN pip install beautifulsoup4
RUN apt-get install -y \
    gcovr \
    cmake 
    
        
WORKDIR /workspace

