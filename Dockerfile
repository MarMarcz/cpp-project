# Użyj oficjalnego obrazu Jenkins LTS jako bazowego
FROM jenkins/jenkins:lts

# Przełącz się na użytkownika root, aby móc instalować pakiety
USER root

# Zaktualizuj repozytoria, zainstaluj potrzebne narzędzia i napraw uprawnienia
RUN apt-get update && \
    mkdir -p /var/lib/apt/lists/partial && \
    apt-get install -y \
    build-essential \
    cmake \
    gcovr \
    cppcheck \
 && rm -rf /var/lib/apt/lists/*

# Upewnij się, że katalogi, w których Jenkins działa, są dostępne
RUN mkdir -p /var/jenkins_home
RUN chown -R jenkins:jenkins /var/jenkins_home

# Przełącz się z powrotem na użytkownika jenkins
USER jenkins
