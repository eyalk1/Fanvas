from os import path

sfml_libs = ["sfml-system", "sfml-window", "sfml-graphics"]
boost_libs = [""]
sanitize_libs = ["asan"]
env = Environment(
    CPPPATH=[path.abspath("include")],
    CXXFLAGS=["-std=c++23", "-O0", "-g", "-fsanitize=address"],
    # LINKER_FLAGS
    LIBS=sanitize_libs + sfml_libs + boost_libs,
    CXX="g++",
    tools=['default','compilation_db']
)

env.CompilationDatabase()
Export(["env", "sfml_libs"])
SConscript(["src/SConscript"])

