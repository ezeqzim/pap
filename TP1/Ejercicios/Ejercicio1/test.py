import sys, os, glob, subprocess, filecmp

folder = "Tests"
in_extension = "in"
big_extension = "big"
expected_extension = "exp"
out_extension = "out"

def main():
    if len(sys.argv) == 1:
		modo_de_uso()
    cpp = find_cpp()
    exe = compile_cpp(cpp)
    if "all" in sys.argv:
        execute_and_compare_tests(exe, load_tests(in_extension))
        execute_tests(exe, load_tests(big_extension))
    elif "func" in sys.argv:
        execute_and_compare_tests(exe, load_tests(in_extension))
    elif "big" in sys.argv:
        execute_tests(exe, load_tests(big_extension))
    else:
        run(exe, sys.argv[1])

def find_cpp():
    return glob.glob("*.cpp")[0]

def compile_cpp(file_path):
    no_ext = remove_ext(file_path)
    subprocess.call("g++ " + file_path + " -o " + no_ext, shell=True)
    return no_ext

def load_tests(extension):
    return glob.glob(folder + "/*." + extension)

def execute_and_compare_tests(exe, tests):
    for test in tests:
        execute_and_compare(exe, test)

def execute_tests(exe, tests):
    for test in tests:
        print "Going to run: " + basename(remove_ext(test))
        execute(exe, test)

def execute_and_compare(exe, test, raise_error = False):
    try:
        execute(exe, test)
        test = remove_ext(test)
        if filecmp.cmp(test + "." + expected_extension, test + "." + out_extension):
            print basename(test) + ": OK"
        else:
            print basename(test) + ": Diff"
    except Exception as inst:
        if raise_error:
            raise
        else:
            print basename(test) + ": ERROR (run only this file to see error)"

def run(exe, test):
    test = folder + "/" + sys.argv[1]
    if os.path.isfile(test + '.' + in_extension):
        execute_and_compare(exe, test + '.' + in_extension, True)
    elif os.path.isfile(test + '.' + big_extension):
        print "Going to run: " + sys.argv[1]
        execute(exe, test + '.' + big_extension)
    else:
        print "File not found in path '" + test + "' with either .in or .big extension"

def execute(exe, test):
	subprocess.call("./" + exe + " < " + test + " > " + remove_ext(test) + "." + out_extension, shell=True)

def modo_de_uso():
    print "Modo de uso:"
    print "1. Usar el parametro all para ejecutar todos los tests en la carpeta " + folder
    print "2. Usar el parametro func para ejecutar todos los tests funcionales en la carpeta " + folder
    print "3. Usar el parametro g para ejecutar todos los tests grandes en la carpeta " + folder
    print "4. Escribir nombre de archivo en la carpeta " + folder + " para solo ejecutar ese test"
    sys.exit()

def remove_ext(file_path):
    return os.path.splitext(file_path)[0]

def basename(file_path):
    return os.path.basename(file_path)

if __name__ == '__main__':
	main()
