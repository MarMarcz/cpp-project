pipeline {
    agent any

    environment {
        PATH = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
        CC = 'gcc'
        CXX = 'g++'
        TEMP_DIR = './temp'  // Temporary directory
    }

    // tools {
    //     // Define CMake tool installation
    //     cmake 'CMake 3.29.6'
    // }

    stages {
        stage('Checkout') {
            steps {
                git branch: 'main', url: 'https://github.com/MarMarcz/cpp-project'
            }
        }
        
        stage('Compile') {
            steps {
                // Skonfiguruj środowisko do kompilacji aplikacji C++
                sh 'make clean' // Przykład dla makefile
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
