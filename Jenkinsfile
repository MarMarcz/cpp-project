pipeline {
    agent any

    environment {
        PATH = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
        CC = 'gcc'
        CXX = 'g++'
    }

    stages {
        stage('Checkout') {
            steps {
                git 'https://github.com/MarMarcz/cpp-project'
            }
        }
        stage('Compile') {
            steps {
                sh 'mkdir build'
                dir('build') {
                    sh 'cmake ../'
                    sh 'make'
                }
            }
        }
        stage('Unit Tests') {
            steps {
                dir('build') {
                    sh 'ctest --output-on-failure'
                }
            }
        }
        stage('Code Coverage') {
            steps {
                dir('build') {
                    sh 'gcovr --root=. --xml --output=coverage.xml'
                    publishHTML([
                        allowMissing: false, 
                        alwaysLinkToLastBuild: true, 
                        keepAll: true, 
                        reportName: 'Code Coverage Report',  // Dodaj nazwę raportu
                        reportDir: '.', 
                        reportFiles: 'coverage.xml'
                    ])
                }
            }
        }
        stage('Static Code Analysis') {
            steps {
                sh 'cppcheck --enable=all src' // analiza statyczna kodu za pomocą cppcheck
            }
        }
        stage('SonarQube Analysis') {
            steps {
                withSonarQubeEnv('SonarQube') {
                    sh 'sonar-scanner'
                }
            }
        }
    }
}
