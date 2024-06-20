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
                        # Ensure we're in the workspace directory where CMakeLists.txt is located
                        cd ${WORKSPACE}
                        echo "Current directory contents:"
                        ls -la
                        # Verify the location of CMakeLists.txt
                        if [ ! -f CMakeLists.txt ]; then
                            echo "CMakeLists.txt not found in workspace directory"
                            exit 1
                        fi

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
                sh 'ctest --output-on-failure'
            }
        }

        stage('Code Coverage') {
            steps {
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
                sh 'cppcheck --enable=all src'
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
