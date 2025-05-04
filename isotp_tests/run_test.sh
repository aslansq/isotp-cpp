thisPath=$(realpath "$0")
thisDirPath=$(dirname "$thisPath")

echoerr() { echo "$@" 1>&2; }

ungracefulExit()
{
    echoerr "$@"
    echoerr ERROR!! $0
    exit 1
}

cd "$thisDirPath" || ungracefulExit "Failed to change directory to $thisDirPath"

cmake -B ./build || ungracefulExit "Failed to run cmake"

cmake --build ./build || ungracefulExit "Failed to build the project"

cd ./build || ungracefulExit "Failed to change directory to $thisDirPath/build"

# Run the tests
ctest --output-on-failure || ungracefulExit "Failed to run ctest"
