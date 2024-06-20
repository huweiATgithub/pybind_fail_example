import promote

a = promote.math.ArrayDynamic(4)

print("Calling set_data now...")

a.set_data([1.0, 2.0, 3.0, 4.0])
print(a.data())

print("Finish set_data")