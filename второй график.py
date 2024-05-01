import matplotlib.pyplot as plt
import pandas as pd
population_data = {
    "Age": ["0-4", "5-9", "10-14", "15-19", "20-24", "25-29", "30-34", "35-39", "40-44", "45-49", "50-54", "55-59", "60-64", "65-69", "70-74", "75-79", "80-84", "85-89", "90-94", "95-99", "100+"],
    "Male": [4155269, 4907942, 4231202, 3712332, 3446216, 4400971, 6272098, 6016923, 5296140, 4752383, 4163442, 4446535, 4376545, 3254754, 2145434, 826548, 946965, 325238, 144025, 33733, 9712],
    "Female": [3923654, 4654970, 4055478, 3575648, 3329784, 4191285, 6151363, 6113885, 5619054, 5227528, 4729046, 5465876, 5965989, 5215570, 4065986, 1877315, 2666012, 1033017, 486569, 98198, 20639],
}

population_df = pd.DataFrame(population_data)

fig = plt.figure(figsize=(15,10))

plt.barh(y=population_df["Age"], width=population_df["Male"], color="#4682b4", label="Male")
plt.barh(y=population_df["Age"], width=-population_df["Female"], color="#ee7a87", label="Female")

plt.text(800000, 20, "Male", fontsize=25, fontweight="bold")
plt.text(-3000000, 20, "Female", fontsize=25, fontweight="bold")
plt.xlim(-1000000, 1000000)
plt.xticks([-8000000, -6000000, -4000000, -2000000, 0, 2000000, 4000000, 6000000, 8000000],
           ["800к", "600к", "400к", "200к", "0", "200к", "400к", "600к", "800к"])

plt.legend(loc="best")
plt.xlabel("Population", fontsize=16, fontweight="bold")
plt.ylabel("Age Range", fontsize=16, fontweight="bold")
plt.title("Population Pyramid Chart for Russia (2020-2024)", loc="left", pad=20, fontsize=25, fontweight="bold")

plt.show()
