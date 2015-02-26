<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // get stock infomation for the shares to be sold
        $stock = lookup($_POST["symbol"]);

        // select the number of shares of this specific stock the user owns
        $rows = query("SELECT * FROM portfolio WHERE id = ? AND symbol = ?",
            $_SESSION["id"], $_POST["symbol"]);
        $total_shares = $rows[0]["shares"];

        // delete shares from portfolio.
        $rows = query("DELETE FROM portfolio WHERE id = ? AND symbol = ?",
            $_SESSION["id"], $_POST["symbol"]);

        // update total cash with proceeds of sale
        $price_shares_total = $stock["price"]*$total_shares;
        $rows = query("UPDATE users SET cash = cash + ? WHERE id = ?",
            $price_shares_total, $_SESSION["id"]);

        // update the history table with this transaction
        $rows = query("INSERT INTO history (id, transaction, symbol, shares, price)
            VALUES(?, ?, ?, ?, ?)",
            $_SESSION["id"], "SELL", $_POST["symbol"], $total_shares, $stock["price"]);

        // redirect to portfolio
        redirect("/");
    }
    else
    {
        // select all the stocks the user owns
        $rows = query("SELECT symbol, shares FROM portfolio WHERE id = ?", $_SESSION["id"]);

        // create the postions associative array for the template to
        // loop through for display of portfolio information.
        $positions = [];
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
                $price_shares_total = $stock["price"]*$row["shares"];
                $total = number_format($price_shares_total, 2, '.', '');;
                $positions[] = [
                    "name" => $stock["name"],
                    "price" => $stock["price"],
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"],
                    "total" => $total
                ];
            }
        }

        // render portfolio
        render("sell_form.php", ["positions" => $positions, "title" => "Sell"]);
    }
?>
