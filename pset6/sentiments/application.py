from flask import Flask, redirect, render_template, request, url_for

import os
import sys
import helpers
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    analyzer = Analyzer(positives, negatives)
    
    tweets = helpers.get_user_timeline(screen_name, 100)
    
    if tweets == None:
        return redirect(url_for("index"))
        
    positive, negative, neutral = 0, 0, 0
    
    for tweet in tweets:
        score = analyzer.analyze(tweet)
        if score > 0.0:
            positive += 1
        elif score < 0.0:
            negative += 1
        else:
            neutral += 1

    chart = helpers.chart(positive, negative, neutral)

    return render_template("search.html", chart=chart, screen_name=screen_name)