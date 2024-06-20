pipeline {
    agent any

    environment {
        PATH = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
        CC = 'gcc'   // Kompilator C
        CXX = 'g++'  // Kompilator C++
    }

    stages {
        stage('Checkout') {
            steps {
                git branch: 'main', url: 'https://github.com/MarMarcz/cpp-project'
            }
        }

        stage('Install Dependencies') {
            steps {
                script {
                    // Instalacja narzędzi kompilacyjnych i inne zależności
                    if (isUnix()) {
                        sh 'apt-get update && apt-get install -y build-essential cmake gcovr cppcheck'
                    } else {
                        error "Installation steps for non-Unix systems are not defined."
                    }
                }
            }
        }

        stage('Compile') {
            steps {
                sh 'make clean'  // Czyszczenie wcześniejszych kompilacji (jeśli używasz make)
                sh 'make'        // Kompilacja kodu
            }
        }

        stage('Unit Tests') {
            steps {
                // Wykonanie testów jednostkowych, np. przy użyciu ctest
                sh 'ctest --output-on-failure'
            }
        }

        stage('Code Coverage') {
            steps {
                // Generowanie raportu pokrycia kodu, np. przy użyciu gcovr
                sh 'gcovr --root=. --xml --output=coverage.xml'
                publishHTML(target: [
                    allowMissing: false,
                    alwaysLinkToLastBuild: true,
                    keepAll: true,
                    reportDir: '.',
                    reportFiles: 'coverage.xml',
                    reportName: 'Code Coverage Report'
                ])
            }
        }

        stage('Static Code Analysis') {
            steps {
                // Analiza statyczna kodu, np. przy użyciu cppcheck
                sh 'cppcheck --enable=all src'
            }
        }

        stage('SonarQube Analysis') {
            steps {
                // Konfiguracja SonarQube i wysłanie kodu do analizy
                withCredentials([string(credentialsId: 'sonarqube-token', variable: 'SONAR_TOKEN')]) {
                    withSonarQubeEnv('SonarQube') {
                        sh 'sonar-scanner -Dsonar.login=$SONAR_TOKEN'
                    }
                }
            }
        }
    }
}
