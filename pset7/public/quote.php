<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // lookup a stock quote
        $stock = lookup($_POST["symbol"]);

        if ($stock === false)
        {
            apologize("You must provide a valid stock symbol.");
        }
        else
        {
            // render stock information
            $symbol = $stock["symbol"];
            $name = $stock["name"];
            $price = $stock["price"];
            $price = number_format($price, 2, '.', '');
            render("stock_info.php", ["symbol" => $symbol, "name" => $name,
                "price" => $price]);
        }
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Log In"]);
    }

?>
