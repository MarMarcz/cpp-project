FROM jenkins/jenkins:lts

USER root

# Install necessary tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gcovr \
    cppcheck

# Switch back to the jenkins user
USER jenkins