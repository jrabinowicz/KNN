import mylib

if __name__ == '__main__':
    # Usar función que espera lista
    print("Usando print_list")
    mylib.print_list([1, 2, 3, 4])
    print("Usando print_vec")
    mylib.print_vec([1, 2, 3, 4])
    print("Usando print_vec con argumento malformado")
    arg = [1, 2, 3, "4"]
    try:
        mylib.print_vec(arg)
    except TypeError as e:
        print("Error:")
        print(e)
