import java.sql.*;
import java.time.Duration;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util. *;

import static java.sql.Timestamp.*;

public class Auction {
    private static Scanner scanner = new Scanner(System.in);
    private static String username;
    private static Connection conn;

    enum Category {
        ELECTRONICS,
        BOOKS,
        HOME,
        CLOTHING,
        SPORTINGGOODS,
        OTHERS
    }
    enum Condition {
        NEW,
        LIKE_NEW,
        GOOD,
        ACCEPTABLE
    }

    private static final String[] cate = { /* use for print category */
            "Electronics", "Books", "Home", "Clothing", "Sporting Goods", "Others"
    };
    private static final String[] cond = { /* use for print condition */
            "New", "Like-new", "Good", "Acceptable"
    };

    private static boolean LoginMenu() {
        String userpass, isAdmin;

        System.out.print("----< User Login >\n" +
                " ** To go back, enter 'back' in user ID.\n" +
                "     user ID: ");
        try{
            username = scanner.next();
            scanner.nextLine();

            if(username.equalsIgnoreCase("back")){
                return false;
            }

            System.out.print("     password: ");
            userpass = scanner.next();
            scanner.nextLine();
        }catch (java.util.InputMismatchException e) {
            System.out.println("Error: Invalid input is entered. Try again.");
            username = null;
            return false;
        }

        /* Your code should come here to check ID and password */
        try {
			/* Get user data from database with entered input id */
            PreparedStatement pstmt = conn.prepareStatement("SELECT password FROM \"user\" WHERE id=?");
            pstmt.setString(1, username);
            ResultSet rst = pstmt.executeQuery();
            if(rst.next() && userpass.equals(rst.getString("password"))){ /* If password is correct, then return true */
                System.out.println("You are successfully logged in.\n");
                return true;
            }
        } catch (SQLException sqle){
            System.out.println(sqle);
            return false;
        }
        /* If password is incorrect, then return false */
        System.out.println("Error: Incorrect user name or password");
        username = null;
        return false;
    }

    private static boolean SellMenu() throws SQLException {
        Category category = null;
        Condition condition = null;
        char choice;
        int price;
        boolean flag_catg = true, flag_cond = true;
        String description;
        do{
            System.out.println(
                    "----< Sell Item >\n" +
                            "---- Choose a category.\n" +
                            "    1. Electronics\n" +
                            "    2. Books\n" +
                            "    3. Home\n" +
                            "    4. Clothing\n" +
                            "    5. Sporting Goods\n" +
                            "    6. Other Categories\n" +
                            "    P. Go Back to Previous Menu"
            );

            try {
                choice = scanner.next().charAt(0);;
            }catch (java.util.InputMismatchException e) {
                System.out.println("Error: Invalid input is entered. Try again.");
                continue;
            }

            flag_catg = true;

            switch ((int) choice){
                case '1':
                    category = Category.ELECTRONICS;
                    continue;
                case '2':
                    category = Category.BOOKS;
                    continue;
                case '3':
                    category = Category.HOME;
                    continue;
                case '4':
                    category = Category.CLOTHING;
                    continue;
                case '5':
                    category = Category.SPORTINGGOODS;
                    continue;
                case '6':
                    category = Category.OTHERS;
                    continue;
                case 'p':
                case 'P':
                    return false;
                default:
                    System.out.println("Error: Invalid input is entered. Try again.");
                    flag_catg = false;
                    continue;
            }
        }while(!flag_catg);

        do{
            System.out.println(
                    "---- Select the condition of the item to sell.\n" +
                            "   1. New\n" +
                            "   2. Like-new\n" +
                            "   3. Used (Good)\n" +
                            "   4. Used (Acceptable)\n" +
                            "   P. Go Back to Previous Menu"
            );

            try {
                choice = scanner.next().charAt(0);;
                scanner.nextLine();
            }catch (java.util.InputMismatchException e) {
                System.out.println("Error: Invalid input is entered. Try again.");
                continue;
            }

            flag_cond = true;

            switch (choice) {
                case '1':
                    condition = Condition.NEW;
                    break;
                case '2':
                    condition = Condition.LIKE_NEW;
                    break;
                case '3':
                    condition = Condition.GOOD;
                    break;
                case '4':
                    condition = Condition.ACCEPTABLE;
                    break;
                case 'p':
                case 'P':
                    return false;
                default:
                    System.out.println("Error: Invalid input is entered. Try again.");
                    flag_cond = false;
                    continue;
            }
        }while(!flag_cond);

		/* Extracted for use in subsequent code */
        DateTimeFormatter formatter;
        LocalDateTime dateTime;
        try {
            System.out.println("---- Description of the item (one line): ");
            description = scanner.nextLine();
            System.out.println("---- Buy-It-Now price: ");

            while (!scanner.hasNextInt()) {
                scanner.next();
                System.out.println("Invalid input is entered. Please enter Buy-It-Now price: ");
            }

            price = scanner.nextInt();
            scanner.nextLine();

            System.out.print("---- Bid closing date and time (YYYY-MM-DD HH:MM): ");
            // you may assume users always enter valid date/time
            String date = scanner.nextLine();  /* "2023-03-04 11:30"; */
            formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
            dateTime = LocalDateTime.parse(date, formatter);
			if(dateTime.isBefore(LocalDateTime.now())){ /* If entered date is already passed, then print "Bid Ended." */
				System.out.println("Bid Ended.");
				return false;
			}
        }catch (Exception e) {
            System.out.println("Error: Invalid input is entered. Going back to the previous menu.");
            return false;
        }

        /* TODO: Your code should come here to store the user inputs in your database */
        try{
            /* Sell item using SQL function, argument is (username, description, category, condition, price, close_date)
			 * Sell function insert into item table and bid table, because new inserted item should be open.
			 */
            PreparedStatement pstmt = conn.prepareStatement("SELECT Sell(?, ?, ?, ?, ?, ?)");
            pstmt.setString(1, username);
            pstmt.setString(2, description);
            pstmt.setString(3, cate[category.ordinal()]);
            pstmt.setString(4, cond[condition.ordinal()]);
            pstmt.setInt(5, price);
            pstmt.setTimestamp(6, Timestamp.valueOf(dateTime));
            pstmt.execute();
        } catch(SQLException sqle){ /* If error occured, then rollback */
            conn.rollback();
            System.out.println(sqle);
            return false;
        }
        /* If queries are successfully executed, then commit and print success message. */
        conn.commit();
        System.out.println("Your item has been successfully listed.\n");
        return true;
    }

    private static boolean SignupMenu() throws SQLException {
        /* 2. Sign Up */
        String new_username, userpass, isAdmin;
        System.out.print("----< Sign Up >\n" +
                " ** To go back, enter 'back' in user ID.\n" +
                "---- user name: ");
        try {
            new_username = scanner.next();
            scanner.nextLine();
            if(new_username.equalsIgnoreCase("back")){
                return false;
            }
            System.out.print("---- password: ");
            userpass = scanner.next();
            scanner.nextLine();
            System.out.print("---- In this user an administrator? (Y/N): ");
            isAdmin = scanner.next();
            scanner.nextLine();
        } catch (java.util.InputMismatchException e) {
            System.out.println("Error: Invalid input is entered. Please select again.");
            return false;
        }

        /* TODO: Your code should come here to create a user account in your database */
        boolean admin = false;
        if(isAdmin.equals("y") || isAdmin.equals("Y")){ /* If entered admin flag is Y/y */
            admin = true;
        }
        try {
            /* Insert into user table with username, password, and admin flag */
            PreparedStatement pstmt = conn.prepareStatement("INSERT INTO \"user\" VALUES(?, ?, ?)");
            pstmt.setString(1, new_username);
            pstmt.setString(2, userpass);
            pstmt.setBoolean(3, admin);
            pstmt.executeUpdate();
        } catch(SQLException sqle){
			/* If error occured when insert into user table, then rollback.
			 * Possible error case is primary key violation of table == duplicate id entered.
			 */
            conn.rollback();
            System.out.println(sqle);
            System.out.println("ID is already exists.");
            return false;
        }
		/* If insert query successfully passed, then commit and print success message */
        conn.commit();
        System.out.println("Your account has been successfully created.\n");
        return true;
    }

    private static boolean AdminMenu() throws SQLException {
        /* 3. Login as Administrator */
        char choice;
        String adminname, adminpass;
        String keyword, seller;
        System.out.print("----< Login as Administrator >\n" +
                " ** To go back, enter 'back' in user ID.\n" +
                "---- admin ID: ");

        try {
            adminname = scanner.next();
            scanner.nextLine();
            if(adminname.equalsIgnoreCase("back")){
                return false;
            }
            System.out.print("---- password: ");
            adminpass = scanner.nextLine();
            // TODO: check the admin's account and password.
        } catch (java.util.InputMismatchException e) {
            System.out.println("Error: Invalid input is entered. Try again.");
            return false;
        }

        try {
            /* Get all attribute of user table with entered user id */
            PreparedStatement pstmt = conn.prepareStatement("SELECT * FROM \"user\" WHERE id=?");
            pstmt.setString(1, adminname);
            ResultSet rst = pstmt.executeQuery();
            rst.next();
            if(!rst.getBoolean("admin")){
				/* If entered user's admin flag is false, then print error message and return false */
                System.out.println("Your ID is not administrator");
                return false;
            }
            if(!adminpass.equals(rst.getString("password"))){
				/* If entered user's id is admin but password is incorrect, then print error message and return false */
                System.out.println("Password is wrong! Try again.");
                return false;
            }
        } catch (SQLException sqle){
			/* If the entered id is not exist, then error occured, so print error message and return false */
            System.out.println("Your ID is not registered. Please sign up first");
            return false;
        }

        do {
			/* Update item bid data that passed close date/time */
			try{
				Statement close_bid = conn.createStatement();
				close_bid.executeQuery("SELECT Update_bid()");
			} catch (SQLException sqle){
				conn.rollback();
				System.out.println(sqle);
				return false;
			}
			conn.commit();

            System.out.println(
                    "----< Admin menu > \n" +
                            "    1. Print Sold Items per Category \n" +
                            "    2. Print Account Balance for Seller \n" +
                            "    3. Print Seller Ranking \n" +
                            "    4. Print Buyer Ranking \n" +
                            "    P. Go Back to Previous Menu"
            );

            try {
                choice = scanner.next().charAt(0);;
                scanner.nextLine();
            } catch (java.util.InputMismatchException e) {
                System.out.println("Error: Invalid input is entered. Try again.");
                continue;
            }

            PreparedStatement pstmt;
            ResultSet rst;
            if(choice == '1'){
                System.out.println("----Enter Category to search : ");
                keyword = scanner.nextLine();
                /*TODO: Print Sold Items per Category */
                System.out.println("         sold item         |     sold date     |   seller ID   |   buyer ID   |   price   | commissions ");
                System.out.println("---------------------------+-------------------+---------------+--------------+-----------+-------------");

                try {
                    /* Print all closed item's data */
                    pstmt = conn.prepareStatement("SELECT item.id, description, date, item.seller, buyer, price, comm_fee(price) FROM item JOIN billing ON item.id=billing.item_id WHERE category=?");
                    pstmt.setString(1, keyword);
                    rst = pstmt.executeQuery();
                    while (rst.next()) {
                        System.out.printf(" %25s | %17s | %13s | %12s | %9d | %12d\n",
                                rst.getString("description"),
                                rst.getDate("date"),
                                rst.getString("seller"),
                                rst.getString("buyer"),
                                rst.getInt("price"),
                                rst.getInt("comm_fee"));
                    }
                } catch (SQLException sqle){
                    System.out.println(sqle);
                    return false;
                }
            } else if(choice == '2'){
                /*TODO: Print Account Balance for Seller */
                System.out.println("---- Enter Seller ID to search : ");
                seller = scanner.next();
                scanner.nextLine();
                System.out.println("         sold item         |    sold date    |  buyer ID  |   price   | commissions ");
                System.out.println("---------------------------+-----------------+------------+-----------+-------------");

                /* Print entered seller's solded item's data */
                try {
                    pstmt = conn.prepareStatement("SELECT description, date, buyer, price, comm_fee(price) FROM item JOIN billing ON item.id=billing.item_id WHERE billing.seller=?");
                    pstmt.setString(1, seller);
                    rst = pstmt.executeQuery();
                    while(rst.next()){
                        System.out.printf(" %25s | %15s | %10s | %9d | %12d\n",
                                rst.getString("description"),
                                rst.getDate("date"),
                                rst.getString("buyer"),
                                rst.getInt("price"),
                                rst.getInt("comm_fee"));
                    }
                } catch (SQLException sqle){
                    System.out.println(sqle);
                    return false;
                }
            } else if(choice == '3'){
                /*TODO: Print Seller Ranking */
                System.out.println("   seller ID   | # of items sold | Total Profit (excluding commissions) ");
                System.out.println("---------------+-----------------+--------------------------------------");

                /* Print Top 10 rank of seller */
                try {
                    pstmt = conn.prepareStatement("SELECT seller, count(item_id), sum(price - comm_fee(price)) FROM billing GROUP BY seller ORDER BY sum(price) DESC LIMIT 10");
                    rst = pstmt.executeQuery();
                    while (rst.next()) {
                        System.out.printf(" %13s | %15d | %36d \n",
                                rst.getString("seller"),
                                rst.getInt(2),
                                rst.getInt(3));
                    }
                } catch (SQLException sqle){
                    System.out.println(sqle);
                    return false;
                }
            } else if(choice == '4') {
                /*TODO: Print Buyer Ranking */
                System.out.println("   buyer ID   | # of items purchased | Total Money Spent ");
                System.out.println("--------------+----------------------+-------------------");

                /* Print Top 10 rank of buyer */
                try {
                    pstmt = conn.prepareStatement("SELECT buyer, count(item_id), sum(price) FROM billing GROUP BY buyer ORDER BY SUM(price) DESC LIMIT 10");
                    rst = pstmt.executeQuery();
                    while (rst.next()) {
                        System.out.printf(" %12s | %20d | %17d \n",
                                rst.getString("buyer"),
                                rst.getInt(2),
                                rst.getInt(3));
                    }
                } catch (SQLException sqle){
                    System.out.println(sqle);
                    return false;
                }
            } else if(choice == 'P' || choice == 'p'){
                return false;
            } else {
                System.out.println("Error: Invalid input is entered. Try again.");
                continue;
            }
        } while(true);
    }

    public static void CheckSellStatus(){
        /* TODO: Check the status of the item the current user is selling */

        System.out.println("   item listed in Auction   | bidder (buyer ID) | bidding price | bidding date/time ");
        System.out.println("----------------------------+-------------------+---------------+-------------------");
        try {
            /* Get open bid item data from item and bid table */
            PreparedStatement pstmt = conn.prepareStatement("SELECT description, bidder, bid_price, bid_time, status FROM item JOIN bid ON item.id=bid.item_id WHERE seller=?");
            pstmt.setString(1, username);
            ResultSet rst = pstmt.executeQuery();
            while (rst.next()) {
                System.out.printf(" %26s | %17s | %13d | %9s%9s \n",
                        rst.getString("description"),
                        rst.getString("bidder"),
                        rst.getInt("bid_price"),
                        rst.getDate("bid_time"),
                        rst.getTime("bid_time")
                );
            }
			/* Get close bid item data from item and billing table */
			pstmt = conn.prepareStatement("SELECT description, buyer, price, date, status FROM item JOIN billing ON item.id=billing.item_id WHERE item.seller=?");
			pstmt.setString(1, username);
			rst = pstmt.executeQuery();
			while (rst.next()) {
                System.out.printf(" %26s | %17s | %13d | %9s%9s \n",
                        rst.getString("description"),
                        rst.getString("buyer"),
                        rst.getInt("price"),
                        rst.getDate("date"),
                        rst.getTime("date")
                );
            }
        } catch (SQLException sqle){
            System.out.println(sqle);
        }
    }

    public static boolean BuyItem() throws SQLException {
        Category category = null;
        Condition condition = null;
        int choice;
        int price;
        String keyword, seller, datePosted;
        boolean flag_catg = true, flag_cond = true;
        boolean any_category = false;
        do {

            System.out.println( "----< Select category > : \n" +
                    "    1. Electronics\n"+
                    "    2. Books\n" +
                    "    3. Home\n" +
                    "    4. Clothing\n" +
                    "    5. Sporting Goods\n" +
                    "    6. Other categories\n" +
                    "    7. Any category\n" +
                    "    P. Go Back to Previous Menu"
            		);

            try {
                choice = scanner.next().charAt(0);;
                scanner.nextLine();
            } catch (java.util.InputMismatchException e) {
                System.out.println("Error: Invalid input is entered. Try again.");
                return false;
            }

            flag_catg = true;

            switch (choice) {
                case '1':
                    category = Category.ELECTRONICS;
                    break;
                case '2':
                    category = Category.BOOKS;
                    break;
                case '3':
                    category = Category.HOME;
                    break;
                case '4':
                    category = Category.CLOTHING;
                    break;
                case '5':
                    category = Category.SPORTINGGOODS;
                    break;
                case '6':
                    category = Category.OTHERS;
                    break;
                case '7':
                    any_category = true;
                    break;
                case 'p':
                case 'P':
                    return false;
                default:
                    System.out.println("Error: Invalid input is entered. Try again.");
                    flag_catg = false;
                    continue;
            }
        } while(!flag_catg);

        do {

            System.out.println(
                    "----< Select the condition > \n" +
                            "   1. New\n" +
                            "   2. Like-new\n" +
                            "   3. Used (Good)\n" +
                            "   4. Used (Acceptable)\n" +
                            "   P. Go Back to Previous Menu"
            );
            try {
                choice = scanner.next().charAt(0);;
                scanner.nextLine();
            } catch (java.util.InputMismatchException e) {
                System.out.println("Error: Invalid input is entered. Try again.");
                return false;
            }

            flag_cond = true;

            switch (choice) {
                case '1':
                    condition = Condition.NEW;
                    break;
                case '2':
                    condition = Condition.LIKE_NEW;
                    break;
                case '3':
                    condition = Condition.GOOD;
                    break;
                case '4':
                    condition = Condition.ACCEPTABLE;
                    break;
                case 'p':
                case 'P':
                    return false;
                default:
                    System.out.println("Error: Invalid input is entered. Try again.");
                    flag_cond = false;
                    continue;
            }
        } while(!flag_cond);

        try {
            System.out.println("---- Enter keyword to search the description : ");
            keyword = scanner.next();
            scanner.nextLine();

            System.out.println("---- Enter Seller ID to search : ");
            System.out.println(" ** Enter 'any' if you want to see items from any seller. ");
            seller = scanner.next();
            scanner.nextLine();

            System.out.println("---- Enter date posted (YYYY-MM-DD): ");
            System.out.println(" ** This will search items that have been posted after the designated date.");
            datePosted = scanner.next();
            scanner.nextLine();
        } catch (java.util.InputMismatchException e) {
            System.out.println("Error: Invalid input is entered. Try again.");
            return false;
        }

		
        /* TODO: Query condition: item category */
        /* TODO: Query condition: item condition */
        /* TODO: Query condition: items whose description match the keyword (use LIKE operator) */
        /* TODO: Query condition: items from a particular seller */
        /* TODO: Query condition: posted date of item */
		
        /* TODO: List all items that match the query condition */
        System.out.println(" Item ID |      Item description      |  Condition  |   Seller   | Buy-It-Now | Current Bid | highest bidder |    Time left    |      bid close      ");
        System.out.println("---------+----------------------------+-------------+------------+------------+-------------+----------------+-----------------+---------------------");
		
		/* Before show item list to user, have to update bid data that has already passed close date */
		try{
			Statement close_bid = conn.createStatement();
			close_bid.executeQuery("SELECT Update_bid()");
		} catch (SQLException sqle){
			conn.rollback();
			System.out.println(sqle);
			return false;
		}
		conn.commit();
		
		/* Set condition of query string step by step */
        try{
            Statement stmt = conn.createStatement();
            /* basic query string */
			String query = "SELECT item.id, description, condition, seller, bid_price, bin_price, bidder, close FROM item JOIN bid ON item.id=bid.item_id WHERE item.status=TRUE"
                    + " AND item.condition='" + cond[condition.ordinal()] + "'";
            if(!any_category){
                query = query + " AND item.category='" + cate[category.ordinal()] + "'";
            }
			/* If entered seller id is not 'any', then must add seller id condition. Else, no need to seller condition */
            if(!seller.equals("any")){
                query = query + " AND seller='" + seller + "'";
            }
			/* Condition for searching by description. Find item that has entered keyword in description attribute.
			 * Additionaly, Check item's post date condition with built-in TIMESTAMP conversion function.
			 */
            query = query + " AND description LIKE " + "'%" + keyword + "%'" +
                    " AND post > TO_TIMESTAMP('" + datePosted + "', 'YYYY-MM-DD')";

            ResultSet rst = stmt.executeQuery(query);

			/* For calculate 'Time left', get current time by java function */
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
            LocalDateTime now = LocalDateTime.now(), cl_date;
            Duration interval;
            String left_time;
            while(rst.next()){
                /* Calculate each item's left time to close */
				cl_date = LocalDateTime.parse(rst.getString("close"), dtf);
                interval = Duration.between(now, cl_date);
                left_time = String.format("%d day %d hrs", interval.toDays(), interval.toHoursPart());
				/* Print item's data */
                System.out.printf(" %7s | %26s | %11s | %10s | %10d | %11d | %14s | %15s | %17s\n",
                        rst.getString("id"),
                        rst.getString("description"),
                        rst.getString("condition"),
                        rst.getString("seller"),
                        rst.getInt("bin_price"),
                        rst.getInt("bid_price"),
                        rst.getString("bidder"),
                        left_time,
                        rst.getString("close")
                );
            }
        } catch (SQLException sqle){
            System.out.println(sqle);
            return false;
        }

        System.out.println("---- Select Item ID to buy or bid: ");

        try {
            choice = scanner.nextInt();
            scanner.nextLine();
            System.out.println("     Price: ");
            price = scanner.nextInt();
            scanner.nextLine();
        } catch (java.util.InputMismatchException e) {
            System.out.println("Error: Invalid input is entered. Try again.");
            return false;
        }

        /* TODO: Buy-it-now or bid: If the entered price is higher or equal to Buy-It-Now price, the bid ends. */
        /* Even if the bid price is higher than the Buy-It-Now price, the buyer pays the B-I-N price. */
        try {
			/* Buy item using SQL function, arguments are buyer id, item id, bid price.
			 * And, get return value of function to detect error.
			 */
            CallableStatement cstmt = conn.prepareCall("{? = call Buy(?, ?, ?)}");
            cstmt.registerOutParameter(1, Types.INTEGER);
            cstmt.setString(2, username);
            cstmt.setInt(3, choice);
            cstmt.setInt(4, price);
            cstmt.execute();
            switch (cstmt.getInt(1)) {
                case -1:
					/* Return -1 means that choice(item id) is not exist. */
                    System.out.println("Error: No exist item id. Try again.");
                    return false;
                case 0:
					/* Return 0 means that price is lower than current bid price */
                    System.out.println("Error: Entered price is lower than current bid price. Try again.");
                    return false;
                case 1:
					/* Return 1 means that this user buy with buy-it-now price */
                    System.out.println("Congratulations, the item is yours now.\n");
                    break;
                case 2:
					/* Return 2 means that this user become a highest bidder */
                    System.out.println("Congratulations, you are the highest bidder.\n");
                    break;
                default:
                    System.out.println("Error: SQL function return other value.");
            }
        } catch(SQLException sqle){
			/* If error occured at above execute, then rollback and return false */
            conn.rollback();
            System.out.println(sqle);
            return false;
		}
		/* Else, commit and return true */
        conn.commit();
        return true;
    }

    public static void CheckBuyStatus(){
        /* TODO: Check the status of the item the current buyer is bidding on */
        /* Even if you are outbidded or the bid closing date has passed, all the items this user has bidded on must be displayed */

        System.out.println(" item ID |      item description      | highest bidder | highest bidding price | your bidding price | bid closing date/time");
        System.out.println("---------+----------------------------+----------------+-----------------------+--------------------+----------------------");

        try {
			/* Find item that current user's requested bid data */
            boolean flag = false;
			/* used table in from clause:
			 * 		item: id, description
			 * 		big_log: if this user is not highest bidder or buyer, then check bid log
			 * 		bid: if this user is current highest bidder, then get bidder, bid_price, close attributes
			 * 		billing: if this user is buyer, then get buyer, buy_price, billing.date attribute
			 */
            PreparedStatement pstmt = conn.prepareStatement("SELECT item.id, description, bidder, bid_price, buyer, billing.price as buy_price, bid_log.price AS my_price, close AS bid_close, date AS billing_close FROM item JOIN bid_log ON item.id=bid_log.item_id LEFT OUTER JOIN bid ON item.id=bid.item_id LEFT OUTER JOIN billing ON item.id=billing.item_id WHERE bid_log.user_id=?");
            pstmt.setString(1, username);
            ResultSet rst = pstmt.executeQuery();
            while(rst.next()){
                flag = rst.getString("bidder") == null;
				/* If bid.bidder attribute is null, then true.
				 * This means that closed item's data has deleted from bid table.
				 * So, If bid table's bidder attribute is not exist, then highest bidder and price is exist in billing table
				 */
                System.out.printf(" %7s | %26s | %14s | %21d | %18d | %10s%10s \n",
                        rst.getString("id"),
                        rst.getString("description"),
                        (flag ? rst.getString("buyer") : rst.getString("bidder")),
                        (flag ? rst.getInt("buy_price") : rst.getInt("bid_price")),
                        rst.getInt("my_price"),
                        (flag ? rst.getDate("billing_close") : rst.getDate("bid_close")),
                        (flag ? rst.getTime("billing_close") : rst.getTime("bid_close")));
            }
        } catch(SQLException sqle){
            System.out.println(sqle);
        }
    }

    public static void CheckAccount(){
        /* TODO: Check the balance of the current user.  */
        System.out.println("[Sold Items] \n");
        System.out.println(" item category | item ID |   sold date   |  sold price  |   buyer ID   | commission");
        System.out.println("---------------+---------+---------------+--------------+--------------+------------");
        try {
			/* Get current user's solded items data */
            PreparedStatement pstmt = conn.prepareStatement("SELECT id, category, date, price, buyer, comm_fee(price) FROM item JOIN billing ON item.id=billing.item_id WHERE billing.seller=?");
            pstmt.setString(1, username);
            ResultSet rst = pstmt.executeQuery();

            while(rst.next()){
                System.out.printf(" %13s | %7s | %13s | %12d | %12s | %10d \n",
                        rst.getString("category"),
                        rst.getString("id"),
                        rst.getDate("date"),
                        rst.getInt("price"),
                        rst.getString("buyer"),
                        rst.getInt("comm_fee"));
            }
        } catch (SQLException sqle){
            System.out.println(sqle);
        }

        System.out.println("[Purchased Items] \n");
        System.out.println(" item category | item ID | purchased date |  purchased price  | seller ID ");
        System.out.println("---------------+---------+----------------+-------------------+-----------");
        try {
			/* Get current user's purchased items data */
            PreparedStatement pstmt = conn.prepareStatement("SELECT id, category, date, price, item.seller FROM item JOIN billing ON item.id=billing.item_id WHERE billing.buyer=?");
            pstmt.setString(1, username);
            ResultSet rst = pstmt.executeQuery();

            while(rst.next()){
                System.out.printf(" %13s | %7s | %14s | %16d | %9s \n",
                        rst.getString("category"),
                        rst.getString("id"),
                        rst.getDate("date"),
                        rst.getInt("price"),
                        rst.getString("seller"));
            }
        } catch (SQLException sqle){
            System.out.println(sqle);
        }
    }

    public static void main(String[] args) {
        char choice;
        boolean ret;

        if(args.length<2){
            System.out.println("Usage: java Auction postgres_id password");
            System.exit(1);
        }

        try{
            conn = DriverManager.getConnection("jdbc:postgresql://localhost/"+args[0], args[0], args[1]);
//            Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost/bnam", "bnam", "changethis");
            conn.setAutoCommit(false);
        }
        catch(SQLException e){
            System.out.println("SQLException : " + e);
            System.exit(1);
        }

        do {
            username = null;
            System.out.println(
                    "----< Login menu >\n" +
                            "----(1) Login\n" +
                            "----(2) Sign up\n" +
                            "----(3) Login as Administrator\n" +
                            "----(Q) Quit"
            );

            try {
                choice = scanner.next().charAt(0);;
                scanner.nextLine();
            } catch (java.util.InputMismatchException e) {
                System.out.println("Error: Invalid input is entered. Try again.");
                continue;
            }

            try {
                switch ((int) choice) {
                    case '1':
                        ret = LoginMenu();
                        if(!ret) continue;
                        break;
                    case '2':
                        ret = SignupMenu();
                        if(!ret) continue;
                        break;
                    case '3':
                        ret = AdminMenu();
                        if(!ret) continue;
                    case 'q':
                    case 'Q':
                        System.out.println("Good Bye");
                        /* TODO: close the connection and clean up everything here */
                        conn.close();
                        System.exit(0); /* program exit with normal state */
                    default:
                        System.out.println("Error: Invalid input is entered. Try again.");
                }
            } catch (SQLException e) {
                System.out.println("SQLException : " + e);
            }
        } while (username==null || username.equalsIgnoreCase("back"));

        // logged in as a normal user
        do {
            System.out.println(
                    "---< Main menu > :\n" +
                            "----(1) Sell Item\n" +
                            "----(2) Status of Your Item Listed on Auction\n" +
                            "----(3) Buy Item\n" +
                            "----(4) Check Status of your Bid \n" +
                            "----(5) Check your Account \n" +
                            "----(Q) Quit"
            );

            try {
                choice = scanner.next().charAt(0);;
                scanner.nextLine();
            } catch (java.util.InputMismatchException e) {
                System.out.println("Error: Invalid input is entered. Try again.");
                continue;
            }

            try{
				/* Before show data to user, have to update item bid data that already passed close date. */
				try{
					Statement close_bid = conn.createStatement();
					close_bid.executeQuery("SELECT Update_bid()");
				} catch (SQLException sqle){
					conn.rollback();
					System.out.println(sqle);
				}
				conn.commit();

                switch (choice) {
                    case '1':
                        ret = SellMenu();
                        if(!ret) continue;
                        break;
                    case '2':
                        CheckSellStatus();
                        break;
                    case '3':
                        ret = BuyItem();
                        if(!ret) continue;
                        break;
                    case '4':
                        CheckBuyStatus();
                        break;
                    case '5':
                        CheckAccount();
                        break;
                    case 'q':
                    case 'Q':
                        System.out.println("Good Bye");
                        /* TODO: close the connection and clean up everything here */
                        conn.close();
                        System.exit(0); /* program exit with normal state */
                }
            } catch (SQLException e) {
                System.out.println("SQLException : " + e);
                System.exit(1);
            }
        } while(true);
    } // End of main
} // End of class