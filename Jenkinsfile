pipeline {
    agent {
        label 'testing'
    }
    stages {
        stage('Hello') {
            steps {
                bat """
                    @echo off
                    echo "Hello world"
                    exit /b 0
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
