# Mustafa Can Caliskan, 150200097
# Yusuf Sahin, 150200016



################ IMPLEMENTING PCA ##################
import numpy as np

# Provide normalized data to the pca function
def pca(data, num_components=2):
    # Calculating the covariance matrix
    covariance_matrix = np.cov(data, rowvar=False)
    # Calculating the eigenvalues and eigenvectors
    eigenvalues, eigenvectors = np.linalg.eig(covariance_matrix)

    # Sorting eigenvector and values in the descending order
    idx = eigenvalues.argsort()[::-1]
    eigenvectors = eigenvectors[:, idx]
    eigenvalues = eigenvalues[idx]

    # Selecting the first num_components eigenvectors
    components = eigenvectors[:, 0:num_components]

    # Projecting the data on the components
    projected_data = np.dot(data, components)

    return projected_data, components

########## MACHINE LEARNING MODEL ##################
from sklearn.impute import SimpleImputer
from sklearn.ensemble import RandomForestClassifier
import pandas as pd

# Read the data as Pandas DataFrame
df = pd.read_csv("aps_failure_training_set.csv", na_values="na")
df_test = pd.read_csv("aps_failure_test_set.csv", na_values="na")

# Configurate the data columns
X = df.drop(['id', 'class'], axis=1)
y = df['class']
X_last = df_test.drop(['id'], axis=1)

# Handle missing values using IterativeImputer
imputer = SimpleImputer(strategy='mean')
X_imputed = imputer.fit_transform(X)
X_last_imputed = imputer.transform(X_last)

# Apply Min-Max Normalization to scale the data 
from scalers import minmaxNormalized

X_normalized = minmaxNormalized(X_imputed)
X_last_normalized = minmaxNormalized(X_last_imputed)

#Apply PCA
X_reduced, components = pca(X_normalized, 75)
X_last_reduced = np.dot(X_last_normalized, components)

# Rest of our modal
rfc = RandomForestClassifier(n_estimators=100, random_state=60)
rfc.fit(X_reduced, y)
y_pred = rfc.predict(X_last_reduced)

ids = df_test['id'].tolist()
df_result = pd.DataFrame({
    'id' : ids,
    'class' : y_pred
})

df_result.to_csv('predictionsPCA.csv', index=False)
