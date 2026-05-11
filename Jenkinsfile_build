pipeline {
    agent {
        label 'testing'
    }
    stages {
        stage('Generating Build Files') {
            steps {
                bat """
                    @echo off
                    mkdir build
                    cd build
                    cmake .. -G "Visual Studio 17 2022" -A x64
                """
            }
        }
        stage('Build auth_server') {
            steps {
                bat """
                    @echo off
                    cd build
                    cmake --build . --config Release -t auth_server
                """
            }
        }
        stage('Build content_server') {
            steps {
                bat """
                    @echo off
                    cd build
                    cmake --build . --config Release -t content_server
                """
            }
        }
    }
    post {
        always {
            cleanWs cleanWhenFailure: true, cleanWhenNotBuilt: true, cleanWhenUnstable: true, notFailBuild: true
        }
    }
}
