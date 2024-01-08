def inner_product(u, v):
    counter = 0
    for i in range(len(u)):
        counter += u[i]*v[i]
    return counter

def scalar_multiply(u, scalar):
    result = []
    for i in u:
        result.append(i*scalar)
    return result

def vector_subtraction(u, v):
    result_2 = []
    for i in range(len(u)):
        result_2.append(u[i]-v[i])
    return result_2

def norm(u):
    counter_2 = 0
    for i in u:
        counter_2 += i**2
    return counter_2**(1/2)

def gram_schmidt(A):
    orthogonal_basis = [A[0]]
    for i in range(1,len(A)):
        counter = 0
        hats = []
        while counter < i:
            hat_top = inner_product(A[i], orthogonal_basis[counter])
            hat_bottom = inner_product(orthogonal_basis[counter], orthogonal_basis[counter])
            hat_final = scalar_multiply(orthogonal_basis[counter], hat_top/hat_bottom)
            hats.append(hat_final)
            counter += 1
        result = A[i]
        for hat in hats:
            result = vector_subtraction(result, hat)
        orthogonal_basis.append(result)
    for i in range(len(orthogonal_basis)):
        orthogonal_basis[i] = scalar_multiply(orthogonal_basis[i], 1/norm(orthogonal_basis[i]))
    return orthogonal_basis

print("GRAM SCHMIDT: ", gram_schmidt(([1,2,3],[4,5,6],[7,8,9])))
