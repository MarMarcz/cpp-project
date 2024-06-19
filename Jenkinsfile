pipeline {
    agent any

    environment {
        PATH = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
        CC = 'gcc'
        CXX = 'g++'
        TEMP_DIR = '/var/jenkins_home/workspace/cpp-project/temp'  // Absolute temporary directory path
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        
        stage('Install Dependencies') {
            steps {
                script {
                    // Instalacja narzędzi kompilacyjnych dla systemu Unix
                    if (isUnix()) {
                        sh 'apt-get update && apt-get install -y build-essential'
                    } else {
                        error "Installation steps for non-Unix systems are not defined."
                    }
                }
            }
        }

        stage('Compile') {
            steps {
                sh 'make clean'  // Example for makefile
                sh 'make'
            }
        }

        stage('Unit Tests') {
            steps {
                dir(TEMP_DIR) {
                    sh 'ctest --output-on-failure'
                }
            }
        }

        stage('Code Coverage') {
            steps {
                dir(TEMP_DIR) {
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
        }

        stage('Static Code Analysis') {
            steps {
                dir('cpp-project') {
                    sh 'cppcheck --enable=all src'
                }
            }
        }

        stage('SonarQube Analysis') {
            steps {
                dir('cpp-project') {
                    withSonarQubeEnv('SonarQube') {
                        sh 'sonar-scanner'
                    }
                }
            }
        }
    }
}
