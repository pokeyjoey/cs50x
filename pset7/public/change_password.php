<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["password"]))
        {
            apologize("You must provide your new password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your new password.");
        }
        else if ($_POST["confirmation"] != $_POST["password"])
        {
            apologize("Your new password and confirmation password do not match.");
        }
        
        // Update the password to the new value.
        $rows = query("UPDATE users SET hash = ? where id = ?", crypt($_POST["password"]), $_SESSION["id"]);

        // redirect to portfolio
        redirect("/");
    }
    else
    {
        // else render form
        render("change_password_form.php", ["title" => "Change Password"]);
    }

?>
