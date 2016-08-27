import sys, os, glob, subprocess, filecmp

folder = "Tests"
in_extension = "in"
expected_extension = "exp"
out_extension = "out"

def main():
    if len(sys.argv) == 1:
		modo_de_uso()
    cpp = find_cpp()
    exe = compile_cpp(cpp)
    if "all" in sys.argv:
        tests = load_tests()
        execute_and_compare_tests(exe, tests)
    else:
        test = folder + "/" + remove_ext(sys.argv[1])
        execute_and_compare(exe, test, True)

def find_cpp():
    return glob.glob("*.cpp")[0]

def compile_cpp(file_path):
    no_ext = remove_ext(file_path)
    subprocess.call("g++ " + file_path + " -o " + no_ext, shell=True)
    return no_ext

def load_tests():
    return [remove_ext(file_path) for file_path in glob.glob(folder + "/*." + in_extension)]

def execute_and_compare_tests(exe, tests):
    for test in tests:
        execute_and_compare(exe, test)

def execute_and_compare(exe, test, raise_error = False):
    try:
        execute(exe, test)
        if filecmp.cmp(test + "." + expected_extension, test + "." + out_extension):
            print basename(test) + ": OK"
        else:
            print basename(test) + ": Diff"
    except Exception as inst:
        if raise_error:
            raise
        else:
            print basename(test) + ": ERROR (run only this file to see error)"

def modo_de_uso():
    print "Modo de uso:"
    print "1. Agregar parametro all para ejecutar todos los tests en la carpeta " + folder
    print "2. Escribir nombre de archivo en la carpeta " + folder + " para solo ejecutar ese test"
    sys.exit()

def remove_ext(file_path):
    return os.path.splitext(file_path)[0]

def basename(file_path):
    return os.path.basename(file_path)

def execute(exe, test):
    subprocess.call("./" + exe + " < " + test + "." + in_extension + " > " + test + "." + out_extension, shell=True)

if __name__ == '__main__':
	main()
