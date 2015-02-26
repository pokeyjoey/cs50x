<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        else if ($_POST["confirmation"] != $_POST["password"])
        {
            apologize("You password and confirmation password do not match.");
        }
        
        // insert registered user into the users table.
        $rows = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)",
            $_POST["username"], crypt($_POST["password"]));

        // if user already exists, query result will be false.
        if ($rows === false) {
            // query database for user
            $rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);

            // if we found user, log them in and redirect to home.
            if (count($rows) == 1)
            {
                // first (and only) row
                $row = $rows[0];

                // compare hash of user's input against hash that's in database
                if (crypt($_POST["password"], $row["hash"]) == $row["hash"])
                {
                    // remember that user's now logged in by storing user's ID in session
                    $_SESSION["id"] = $row["id"];

                    // redirect to portfolio
                    redirect("/");
                }
            }
        }
        else
        {
            // remember that user's now logged in by storing user's ID in session
            $rows = query("SELECT LAST_INSERT_ID() as id");
            $_SESSION["id"] = $rows[0]["id"];

            // redirect to portfolio
            redirect("/");
        }
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
