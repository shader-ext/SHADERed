@echo off
setlocal

:: Check input parameter (gen or build)
set MODE=build
if not "%1"=="" set MODE=%1

:: Select build type (Debug or Release)
set BUILD_TYPE=Debug
if not "%2"=="" set BUILD_TYPE=%2

echo =========================================
echo SHADERed Build Script
echo Mode: %MODE%
echo Build Type: %BUILD_TYPE%
echo =========================================

:: If only generating the Visual Studio project
if "%MODE%"=="gen" (
    echo Generating Visual Studio project...

    :: Remove old build directory if it exists
    if exist build (
        echo Removing old build directory...
        rmdir /s /q build
    )

    :: Create new build directory
    mkdir build
    cd build

    :: Run CMake to generate Visual Studio 2022 project
    cmake -G "Visual Studio 17 2022" -S .. -B .

    :: Return to the root directory
    cd ..

    echo =========================================
    echo Visual Studio project generated successfully!
    echo =========================================

    endlocal
    exit /b 0
)

:: If mode is "build", generate first and then build
if "%MODE%"=="build" (
    echo Generating Visual Studio project and building...

    :: Remove old build directory if it exists
    if exist build (
        echo Removing old build directory...
        rmdir /s /q build
    )

    :: Create new build directory
    mkdir build
    cd build

    :: Run CMake to generate Visual Studio 2022 project
    cmake -G "Visual Studio 17 2022" -S .. -B .

    :: Build the project with the specified build type
    cmake --build . --config %BUILD_TYPE%

    :: Return to the root directory
    cd ..

    echo =========================================
    echo Build completed successfully! (%BUILD_TYPE%)
    echo =========================================

    endlocal
    exit /b 0
)

:: If an invalid parameter is provided
echo ERROR: Invalid mode! Use "gen" to generate the project or "build" to build.
endlocal
exit /b 1