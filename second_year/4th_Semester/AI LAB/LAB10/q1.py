import numpy as np
from fontTools.ttLib.tables.otConverters import AATLookup
from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split

# MACRO PARAMETERS - MODIFY THESE AS NEEDED
DEFAULT_W = 0.7
DEFAULT_C1 = 1.5
DEFAULT_C2 = 1.5
DEFAULT_NUM_PARTICLES = 50
DEFAULT_NUM_ITERATIONS = 2000

# Load and split data
boston = fetch_openml(name='boston', version=1, as_frame=False)
X = np.array(boston.data, dtype=np.float64)  # Explicit data type conversion
y = np.array(boston.target, dtype=np.float64)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Use macro parameters
w = DEFAULT_W
c1 = DEFAULT_C1
c2 = DEFAULT_C2
num_particles = DEFAULT_NUM_PARTICLES
num_iterations = DEFAULT_NUM_ITERATIONS

n_features = X_train.shape[1]
n_weights = n_features + 1  # Including bias term

# Initialize swarm
np.random.seed(42)
swarm = []
for _ in range(num_particles):
    position = np.random.uniform(-10, 10, n_weights)
    velocity = np.random.uniform(-1, 1, n_weights)

    # Use np.dot() for matrix multiplication
    y_pred = np.dot(X_train, position[1:]) + position[0]
    mse = np.mean((y_pred - y_train) ** 2)

    swarm.append({
        'position': position,
        'velocity': velocity,
        'pbest_pos': position.copy(),
        'pbest_score': mse
    })

# Initialize global best
gbest_pos = None
gbest_score = float('inf')
for particle in swarm:
    if particle['pbest_score'] < gbest_score:
        gbest_score = particle['pbest_score']
        gbest_pos = particle['pbest_pos'].copy()

# PSO optimization
for _ in range(num_iterations):
    for particle in swarm:
        # Use np.dot() for matrix multiplication
        y_pred = np.dot(X_train, particle['position'][1:]) + particle['position'][0]
        current_mse = np.mean((y_pred - y_train) ** 2)

        # Update personal best
        if current_mse < particle['pbest_score']:
            particle['pbest_score'] = current_mse
            particle['pbest_pos'] = particle['position'].copy()

            # Update global best
            if current_mse < gbest_score:
                gbest_score = current_mse
                gbest_pos = particle['pbest_pos'].copy()

        # Update velocity
        r1 = np.random.rand(n_weights)
        r2 = np.random.rand(n_weights)
        cognitive = c1 * r1 * (particle['pbest_pos'] - particle['position'])
        social = c2 * r2 * (gbest_pos - particle['position'])
        particle['velocity'] = w * particle['velocity'] + cognitive + social

        # Update position with clamping
        particle['position'] += particle['velocity']
        particle['position'] = np.clip(particle['position'], -10, 10)

# Final evaluation using np.dot()
y_train_pred = np.dot(X_train, gbest_pos[1:]) + gbest_pos[0]
train_mse = np.mean((y_train_pred - y_train) ** 2)

y_test_pred = np.dot(X_test, gbest_pos[1:]) + gbest_pos[0]
test_mse = np.mean((y_test_pred - y_test) ** 2)

# Format output
rounded_weights = [round(weight, 3) for weight in gbest_pos]
print(f"Best Weights: {rounded_weights}")
print(f"Training MSE: {round(train_mse, 2)}")
print(f"Testing MSE: {round(test_mse, 2)}")

print("AI = BB, AA = 12")
print("DBMS = AB, AB = 9")
print("OS = AA, AA = 0")
print("CHE = BB = 12")
print("ECO = AA = 0")
print("MA = AA = 0")