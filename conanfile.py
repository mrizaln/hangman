from conan import ConanFile
from conan.tools.cmake import cmake_layout

class Recipe(ConanFile):
    settings   = ["os", "compiler", "build_type", "arch"]
    generators = ["CMakeToolchain", "CMakeDeps"]
    requires   = ["fmt/11.0.2", "cli11/2.4.2"]

    default_options = { "cli11/*:header_only": False }

    def layout(self):
        cmake_layout(self)
