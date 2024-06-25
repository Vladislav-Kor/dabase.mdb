use mdbtools_rs::{MdbTools, MdbQuery};

fn main() {
    let mdb_file = "./dabase.mdb";
    let query = "SELECT * FROM police";

    let mut mdb_tools = MdbTools::new(mdb_file).unwrap();
    let result = mdb_tools.query(query).unwrap();

    for row in result {
        for col in row {
            println!("{}", col);
        }
        println!("---");
    }
}