<?php

    // configuration
    require("../includes/config.php"); 

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
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio"]);

?>
