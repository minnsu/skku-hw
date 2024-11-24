public class Racer implements Runnable {

	public  String winner;
	public void race(){
			
	}

	private boolean isRaceWon(int totalDistanceCovered){
		boolean isRaceWon =  false;
		if((winner==null )&&(totalDistanceCovered==100)){
				String winnerName = Thread.currentThread().getName();
				winner = winnerName; //setting the winner name
				System.out.println("Winner is :"+winner);
				isRaceWon = true;
			}else if(winner==null){
			isRaceWon = false;
			}else if(winner!=null){
				isRaceWon = true;
			}
		return isRaceWon;
		}

	@Override
	public void run() {
		for(int distance=1;distance<=100;distance++){
			boolean isRaceWon = this.isRaceWon(distance);
			 
			if(isRaceWon){
				break;
			}
			System.out.println("Distance Covered by "+
		Thread.currentThread().getName()+ " is:"+distance +"meters");
		//Check if race is complete if some one has already won
		
	}

	}

}
