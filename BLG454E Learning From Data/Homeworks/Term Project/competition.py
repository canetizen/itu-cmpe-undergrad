# Mustafa Can Caliskan, 150200097
# Yusuf Sahin, 150200016

from imblearn.under_sampling import RandomUnderSampler
from sklearn.ensemble import RandomForestClassifier
from sklearn.impute import SimpleImputer
import pandas as pd

df = pd.read_csv("aps_failure_training_set.csv", na_values="na")
df_test = pd.read_csv("aps_failure_test_set.csv", na_values="na")

X = df.drop(['id', 'class'], axis=1)
y = df['class']
X_last = df_test.drop(['id'], axis=1)

threshold = 0.67
missing_portion = df.isnull().mean()
cols_to_drop = missing_portion[missing_portion > threshold].index
X = X.drop(cols_to_drop, axis=1)
X_last = X_last.drop(cols_to_drop, axis=1)

rus = RandomUnderSampler(random_state=60)
X_res, y_res = rus.fit_resample(X, y)

imputer = SimpleImputer(strategy='median')
X_res = imputer.fit_transform(X_res)
X_last = imputer.fit_transform(X_last)

rfc = RandomForestClassifier(n_estimators=100, random_state=60)
rfc.fit(X_res, y_res)
y_pred = rfc.predict(X_last)

ids = df_test['id'].tolist()
df_result = pd.DataFrame({
    'id' : ids,
    'class' : y_pred
})

df_result.to_csv('predictions.csv', index=False)
