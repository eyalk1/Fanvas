from os import path, environ

sfml_libs = ["sfml-system", "sfml-window", "sfml-graphics"]
boost_libs = [""]
sanitize_libs = ["asan"]
env = Environment(
    ENV = {'PATH' : environ['PATH']},
    CPPPATH=[path.abspath("include"), '/usr/local/include'],
    CXXFLAGS=["-Wall","-Wextra","-Werror","-std=c++2b", "-O0", "-g"], #, "-stdlib=libc++"],
    # LINKFLAGS=[--ld-path=/usr/local/bin/ld.lld", "-v"],
    LIBS=sanitize_libs + sfml_libs + boost_libs,
    LIBPATH=['/usr/local/lib'],
    CXX="/usr/bin/g++-12",
    tools=['default','compilation_db'],
)
env.CompilationDatabase()
Export(["env", "sfml_libs"])
SConscript(["src/SConscript"])

