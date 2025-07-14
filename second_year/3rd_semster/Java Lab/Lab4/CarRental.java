import java.util.*;

public class CarRental{
	int carId;
	String carType;
	float rent;
	public CarRental(int carId , String carType){
		this.carId = carId;
		this.carType = carType;
		rent = 0; 
	}
	public void computeRent(){
		if("Small Car".equals(carType)){
			rent = 1000;
		}else if("Van".equals(carType)){
			rent = 800;
		}else if("SUV".equals(carType)){
			rent = 2500;
		}else {
			System.out.println("Invalid car type..");
			rent = 0;
		}
	}
	public void showCar(){
		System.out.println("car ID : " + carId);
		System.out.println("car type : "+ carType);
		System.out.println("rent : "+ rent);
	}
}