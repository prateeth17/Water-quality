from flask import Flask, render_template, request

app = Flask(__name__)

def check_water(pH, turbidity, temp):
    pH_status = "Acceptable" if 6.5 <= pH <= 8.5 else "Not Acceptable"
    turbidity_status = "Acceptable" if turbidity < 1 else "Not Acceptable"
    temp_status = "Acceptable" if 0 <= temp <= 35 else "Not Acceptable"
    overall = "Drinkable" if all(s == "Acceptable" for s in [pH_status, turbidity_status, temp_status]) else "Not Drinkable"
    return pH_status, turbidity_status, temp_status, overall

@app.route("/", methods=["GET", "POST"])
def index():
    result = None
    if request.method == "POST":
        try:
            pH = float(request.form["pH"])
            turbidity = float(request.form["turbidity"])
            temp = float(request.form["temp"])
            pH_status, turbidity_status, temp_status, overall = check_water(pH, turbidity, temp)
            result = {
                "pH": pH, "turbidity": turbidity, "temp": temp,
                "pH_status": pH_status,
                "turbidity_status": turbidity_status,
                "temp_status": temp_status,
                "overall": overall
            }
        except ValueError:
            result = {"error": "Please enter valid numbers."}
    return render_template("index.html", result=result)

if __name__ == "__main__":
    app.run(debug=True)
