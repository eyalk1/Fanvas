from os import path, environ

sfml_libs = ["sfml-system", "sfml-window", "sfml-graphics"]
sanitize_libs = ["asan"]
error_flags = ["-W" + a for a in ["all", "extra", "error", "conversion", "cast-align","cast-qual", "disabled-optimization", "float-equal","format=2","import", "init-self","inline",
"missing-include-dirs", "missing-noreturn", "pointer-arith", "shadow","switch-default","unreachable-code"]]
lib_includes = ["-isystem" + path.abspath('lib-include')]
modules_flags = ['-fmodules-ts']

env = Environment(
    ENV = {'PATH' : environ['PATH']},
    CPPPATH=[path.abspath("include"), '/usr/local/include'],
    CXXFLAGS=lib_includes + error_flags + ["-std=c++2b", "-O0", "-g"] + modules_flags,
    LIBS=sanitize_libs + sfml_libs,
    LIBPATH=['/usr/local/lib'],
    CXX="/usr/bin/g++-12",
    tools=['default','compilation_db'],
)
env.CompilationDatabase()
Export(["env", "sfml_libs"])
SConscript(["lib-src/SConscript", "src/SConscript"])

