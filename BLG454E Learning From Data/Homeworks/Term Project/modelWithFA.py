# Mustafa Can Caliskan, 150200097
# Yusuf Sahin, 150200016



# Implementation of Factor Analysis

import numpy as np

class FactorAnalysis:
    def __init__(self, n_factors):
        self.n_factors = n_factors
        self.loadings = None
        self.unique_variances = None

    def fit(self, X, tol=1e-4, max_iter=1000):
        n, m = X.shape
        self.loadings = np.random.rand(m, self.n_factors)
        self.unique_variances = np.ones(m) * 1e-4  # Initialize with small positive values

        for _ in range(max_iter):
            loadings_prev = self.loadings.copy()
            unique_variances_prev = self.unique_variances.copy()

            # E-step
            epsilon = 1e-8  # Small positive constant
            inv = np.linalg.inv(np.eye(self.n_factors) + self.loadings.T @ np.diag(1 / (self.unique_variances + epsilon)) @ self.loadings)
            W = self.loadings @ inv
            Z = W.T @ (X - X.mean(axis=0)).T  # Transpose here

            # M-step
            self.loadings = (X - X.mean(axis=0)).T @ Z.T @ np.linalg.inv(Z @ Z.T)
            reconstructed_X = (self.loadings @ Z).T + X.mean(axis=0)
            self.unique_variances = np.mean((X - reconstructed_X)**2, axis=0)

            if np.allclose(self.loadings, loadings_prev, atol=tol) and np.allclose(self.unique_variances, unique_variances_prev, atol=tol):
                break

    def transform(self, X):
        epsilon = 1e-8  # Small positive constant
        inv = np.linalg.inv(np.eye(self.n_factors) + self.loadings.T @ np.diag(1 / (self.unique_variances + epsilon)) @ self.loadings)
        W = self.loadings @ inv
        return W.T @ (X - X.mean(axis=0)).T  # Transpose here



    
########## MACHINE LEARNING MODEL ##################
import pandas as pd
from sklearn.impute import SimpleImputer
from sklearn.ensemble import RandomForestClassifier

# Read the dataset
df = pd.read_csv("aps_failure_training_set.csv", na_values="na")
df_test = pd.read_csv("aps_failure_test_set.csv", na_values="na")

# Configurate the data columns
X = df.drop(['id', 'class'], axis=1)
y = df['class']
X_last = df_test.drop(['id'], axis=1)

# Handle missing values using IterativeImputer
imputer = SimpleImputer(strategy='median')
X_imputed = imputer.fit_transform(X)
X_last_imputed = imputer.transform(X_last)

# Apply Factor Analysis
fa = FactorAnalysis(n_factors=2)
fa.fit(X_imputed)
X_transformed = fa.transform(X_imputed)
X_last_transformed = fa.transform(X_last_imputed)

# Train the model
rfc = RandomForestClassifier(n_estimators=100, random_state=60)
rfc.fit(X_transformed, y)

# Make predictions
y_pred = rfc.predict(X_last_transformed)

# Prepare the result
ids = df_test['id'].tolist()
df_result = pd.DataFrame({
    'id' : ids,
    'class' : y_pred
})

# Save the result to a CSV file
df_result.to_csv('predictionsFA.csv', index=False)
