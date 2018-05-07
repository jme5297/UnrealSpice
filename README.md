# UnrealSpice
Unreal Engine integration with the ANSI C build of NASA JPL's SPICE toolkit for pairing high-accuracy spaceflight simulations with a visualization front-end. As of now, this configuration is only compatible Windows x64-based machines.

## Information
This is an example project for linking the ANSI C build of JPL's SPICE library (also referred to as CSPICE) to Unreal Engine. More information on the SPICE toolkit can be found [here](https://naif.jpl.nasa.gov/naif/toolkit.html) and the ANSI C libraries can be downloaded [here](https://naif.jpl.nasa.gov/naif/toolkit_C.html). The hypertext documentation provided in the SPICE library is also hosted online and can be found [here](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/index.html). As a convenience, a precompiled version of the SPICE library can be found in this repository that works with:
* Visual Studio 2017 x64 Compiler
* Unreal Engine v4.19.2

## Recompiling CSPICE Library for Specific MSVC Configuration
* If compiling the x64 version of CSPICE:
  - Start
  - `Developer Command Prompt For <insert VS version here>`
  - Move (`cd`) into the desired VS directory. 
    - Ex: For MSVC 14.0, the directory will be `C:\Program Files (x86)\Microsoft Visual Studio 14.0\`
  - Move into the VC folder (`cd VC`)
  - `vcvarsall.bat amd64`
* If the above does not work, use any other method available to ensure that x64 compiling is enabled.
