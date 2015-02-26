<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("You must buy whole shares of stocks.");
        }

        // get stock infomation for the shares to be sold
        $stock = lookup($_POST["symbol"]);

        // how much cash does the customer have to spend
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $total_cash = $rows[0]["cash"];

        // does the cost of the shares exceed the cash availible to spend ?
        $total_cost_shares = $stock["price"]*$_POST["shares"];
        if ($total_cost_shares > $total_cash)
        {
            apologize("You cant afford to buy that.");
        }

        // update the number of shares of this specific stock the user owns
        $symbol = strtoupper($_POST["symbol"]);
        $rows = query("INSERT INTO portfolio (id, symbol, shares) VALUES(?, ?, ?)
            ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
            $_SESSION["id"], $symbol, $_POST["shares"]);

        // update the history table with this transaction
        $rows = query("INSERT INTO history (id, transaction, symbol, shares, price)
            VALUES(?, ?, ?, ?, ?)",
            $_SESSION["id"], "BUY", $symbol, $_POST["shares"], $stock["price"]);

        // update the total cash that the user now has
        $rows = query("UPDATE users SET cash = cash - ? WHERE id = ?",
            $total_cost_shares, $_SESSION["id"]);

        // redirect to portfolio
        redirect("/");
    }
    else
    {
        // render buy
        render("buy_form.php", ["title" => "Buy"]);
    }
?>
