pipeline {
    agent any

    environment {
        PATH = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
        CC = 'gcc'
        CXX = 'g++'
        TEMP_DIR = '/var/jenkins_home/workspace/cpp-project/temp'  // Absolute temporary directory path /var/jenkins_home/workspace/lab12ex2
    }

    stages {
        stage('Checkout') {
                    steps {
                        git branch: 'main', url: 'https://github.com/MarMarcz/cpp-project'
                        script {
                            sh 'echo "Current workspace contents:"'
                            sh 'ls -la ${WORKSPACE}'
                        }
                    }
                }
        
        stage('Install Dependencies') {
            steps {
                script {
                    // Instalacja narzędzi kompilacyjnych dla systemu Unix
                    if (isUnix()) {
                        sh 'sudo apt-get update && sudo apt-get install -y build-essential cmake gcovr cppcheck'
                    } else {
                        error "Installation steps for non-Unix systems are not defined."
                    }
                }
            }
        }

        stage('Compile') {
                    steps {
                        script {
                            sh '''
                                echo "Entering workspace directory"
                                cd ${WORKSPACE}

                                echo "Current directory contents:"
                                ls -l

                                if [ -f ${WORKSPACE}/CMakeLists.txt ]; then
                                    echo "CMakeLists.txt found in workspace directory"
                                else
                                    echo "CMakeLists.txt not found in workspace directory"
                                    exit 1
                                fi

                                echo "Creating build directory"
                                mkdir -p build
                                cd build
                                cmake ..
                                cmake --build .
                            '''
                        }
                    }
                }

        stage('Unit Tests') {
            steps {
                script {
                    sh '''
                        cd build
                        ls -la
                        ctest --output-on-failure
                    '''
                }
            }
        }

        stage('Code Coverage') {
            steps {
                script {
                    sh '''
                        cd build
                        gcovr --root=. --xml --output=coverage.xml
                    '''
                    publishHTML(target: [
                        allowMissing: false,
                        alwaysLinkToLastBuild: true,
                        keepAll: true,
                        reportDir: 'build',
                        reportFiles: 'coverage.xml',
                        reportName: 'Code Coverage Report'
                    ])
                }
            }
        }

        stage('Static Code Analysis') {
            steps {
                sh 'cppcheck --enable=all --include=src --include=tests src'
            }
        }

        stage('SonarQube Analysis') {
            steps {
                withCredentials([string(credentialsId: 'sonarqube-token', variable: 'SONAR_TOKEN')]) {
                    withSonarQubeEnv('SonarQube') {
                        sh 'sonar-scanner -Dsonar.login=$SONAR_TOKEN'
                    }
                }
            }
        }
    }
}